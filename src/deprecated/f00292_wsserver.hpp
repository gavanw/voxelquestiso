

#ifdef USE_POCO

class WebSocketServer: public Poco::Util::ServerApplication
	/// The main application class.
	///
	/// This class handles command-line arguments and
	/// configuration files.
	/// Start the WebSocketServer executable with the help
	/// option (/help on Windows, --help on Unix) for
	/// the available command line options.
	///
	/// To use the sample configuration file (WebSocketServer.properties),
	/// copy the file to the directory where the WebSocketServer executable
	/// resides. If you start the debug version of the WebSocketServer
	/// (WebSocketServerd[.exe]), you must also create a copy of the configuration
	/// file named WebSocketServerd.properties. In the configuration file, you
	/// can specify the port on which the server is listening (default
	/// 9980) and the format of the date/time string sent back to the client.
	///
	/// To test the WebSocketServer you can use any web browser (http://localhost:9980/).
{
public:

	bool dataReady;
	bool isWorking;
	bool isJSON;
	int MAX_FRAME_SIZE;
	charArr recBuffer;
	charArr okBuffer;
	//int recBufferLength;
	
	//JSONValue* recMessage;

	WebSocketServer(): _helpRequested(false)
	{
		//recMessage = NULL;
		dataReady = false;
		isWorking = false;
		isJSON = false;
		//recBufferLength = 0;
		
		MAX_FRAME_SIZE = 16777216; //16 MB
		recBuffer.data = new char[MAX_FRAME_SIZE];
		okBuffer.data = "{\"cc\":\"REC__OK\"}";
		okBuffer.size = 16;
		
	}
	
	~WebSocketServer()
	{
		if (recBuffer.data != NULL) {
			delete[] recBuffer.data;
		}
	}

	//int main(const std::vector<std::string>& args);

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}
		
	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A sample HTTP server supporting the WebSocket protocol.");
		helpFormatter.format(std::cout);
	}


	int main(const std::vector<std::string>& args)
	{





		// get parameters from configuration file
		unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 9980);
		
		// set-up a server socket
		ServerSocket svs(port);
		// set-up a HTTPServer instance
		HTTPServer srv(new RequestHandlerFactory(this), svs, new HTTPServerParams);
		// start the HTTPServer
		srv.start();
		// wait for CTRL-C or kill
		//waitForTerminationRequest();
		// Stop the HTTPServer

		glutMainLoop();
		
		srv.stop();


		return Application::EXIT_OK;

	}
	
	
private:
	bool _helpRequested;
};
#endif





