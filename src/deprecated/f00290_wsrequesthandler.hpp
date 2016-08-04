


#ifdef USE_POCO
class WebSocketRequestHandler: public HTTPRequestHandler {
public:

	
	WebSocketServer* ws_ptr;
	
	
	

	WebSocketRequestHandler(WebSocketServer* _ws_ptr) {

		ws_ptr = _ws_ptr;
	}
	~WebSocketRequestHandler() {
		
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{

		int flags;
		int n;

		//JSONValue *value;

		if (ws_ptr->isWorking) {
			// drop the request, client should only send one request
			// at a time until it receives a response message
			return;
		}


		ws_ptr->isWorking = true;
		ws_ptr->dataReady = false;
		
		/*
		if (ws_ptr->recMessage != NULL) {
			delete ws_ptr->recMessage;
			ws_ptr->recMessage = NULL;
		}
		*/

		Application& app = Application::instance();

		
		
		try
		{


			WebSocket ws(request, response);
			app.logger().information("WebSocket connection established.");
			//char buffer[1024];
			
			
			
			do
			{
				n = ws.receiveFrame(ws_ptr->recBuffer.data, ws_ptr->MAX_FRAME_SIZE, flags);
				//app.logger().information(Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));
				

				if (n > 0) {

					ws_ptr->recBuffer.data[n+1] = '\0';
					ws_ptr->recBuffer.size = n;

					if (ws_ptr->recBuffer.data[0] == '{') {
						ws_ptr->isJSON = true;
						ws_ptr->recBuffer.data[n] = '\0';
					}
					else {
						ws_ptr->isJSON = false;
					}

					ws_ptr->dataReady = true;

					
					

				}

				ws.sendFrame(ws_ptr->okBuffer.data,ws_ptr->okBuffer.size,flags);

			}
			while ( (n > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE) && PROG_ACTIVE );
			app.logger().information("WebSocket connection closed.");

			

			


		}
		catch (WebSocketException& exc)
		{

			app.logger().log(exc);
			switch (exc.code())
			{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}


		

		


		

	}
};
#else
class WebSocketRequestHandler {
public:
	WebSocketRequestHandler() {
		
	}
};
#endif
