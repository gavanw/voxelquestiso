
class GameMusic {
	public:
		
		
		//sf::SoundBuffer buffer;
		sf::Music sound;
		
		float volume;
		
		GameMusic() {
			
		}
		
		void init(string path) {
			if ( !sound.openFromFile(path) ) {
				cout << "error loading music";
				return;
			}
			
		}
		
		void setLoop(bool val) {
			sound.setLoop(val);
		}

		void stop() {
			sound.stop();
		}
		
		void setVolume(float _volume=1.0f) {
			volume = _volume;
			int intVol = _volume*100.0f;
			sound.setVolume(intVol);
		}
		
		void play(float _volume=1.0f)
		{
			setVolume(_volume);
			sound.play();
		}
};
