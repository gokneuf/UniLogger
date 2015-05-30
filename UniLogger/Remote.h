// Define to export dll functions
#define REMOTE_EXPORTS

#ifdef REMOTE_EXPORTS
#define REMOTE_API __declspec(dllexport)
#else
#define REMOTE_API __declspec(dllimport)
#endif

/* using __cdecl to avoid compiler variations in C++ name mangling. */

extern "C"
{

	struct RX
	{
		char *_label;
	};

	struct System
	{
		// delegate for Omnilink, P25 wide area network, EDACS with overlapping site IDs.
		System *_system;
		// network identity.
		unsigned long _ID;
		// system type
		char *_type;
		// system label
		char *_label;
	};

	struct Site
	{
		// system
		System *_system;
		// site identity.
		unsigned short _ID;
		// system label
		char *_label;
	};

	struct Channel
	{
		// site
		Site *_site;
		// LCN
		unsigned short _ID;
		// system label
		char *_label;
		// frequency in hz
		long _Hz;
		// bandwidth in hz
		int _BW;
		// control channel
		bool _control;
		// voice service class
		char _service;
	};

	struct Address
	{
		// system
		System *_system;
		// address (group or user ID)
		unsigned long _ID;
		// label (description vs. tag)
		char *_label;
		// RGB display color
		long _color;
		// listening priority
		short _rank;
		// talkgroup vs. radio
		bool _group;
	};

	/*
	Called when a voice role receiver is idle.
	The arguments are guaranteed to remain stable for the duration of the function call.
	However, the called function should return ASAP to prevent blocking the application.
	rx - receiver to park on a voice channel.
	ch - conventional voice channel (_site is likely NULL).
	*/
	REMOTE_API void Park(const RX *rx, const Channel *ch);

	/*
	Called when a signal role receiver is following a control channel.
	The arguments are guaranteed to remain stable for the duration of the function call.
	However, the called function should return ASAP to prevent blocking the application.
	rx - receiver chasing a control channel.
	ch - control channel
	*/
	REMOTE_API void Control(const RX *rx, const Channel *ch);

	/*
	Called when a voice role receiver is following a voice channel.
	The arguments are guaranteed to remain stable for the duration of the function call.
	However, the called function should return ASAP to prevent blocking the application.
	rx - receiver chasing a voice channel.
	ch - voice channel
	src - speaking party with radio ID.
	tgt - audience party (may be a talkgroup or radio).
	*/
	REMOTE_API void Listen(const RX *rx, const Channel *ch, const Address *src, const Address *tgt);

	/*
	Log an action
	rx - receiver chasing a voice channel.
	ch - voice channel
	src - speaking party with radio ID.
	tgt - audience party (may be a talkgroup or radio).
	*/
	void Log(char* action, const RX *rx, const Channel *ch, const Address *src, const Address *tgt);

};
