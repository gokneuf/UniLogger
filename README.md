# UniLogger Multiple DLL Version
Credit to [Dreinhold]'s Multiple DLL version and [UniLogger 1.2].
###About
Remote.DLL allows multiple copies of Trunking Recorder to record multiple Voice Receivers in Unitrunker, with only one Unitrunker running.
###Requires:
- Might require Visual C++ Redistributable for [Visual Studio 2012 Update 4] to use Remote.DLL, built with Visual Studio 2012 Update 4.
- [Unitrunker]. Testing using Preview version UniTrunker-1.0.31.13.
- [Trunking Recorder].
- Optional:
 - [DSDPlus] or digital decoder for digital decoding

###Installation - Detailed
1. Install and configure Unitrunker
2. Place Remote.DLL in each Voice Receiver folder in Unitrunker. Voice Receiver folders are identified by RXXXXXXXX. To easily locate the Receiver folder, in Unitrunker click on the Voice Receiver then the folder icon. For example, on Windows 7, that path might be "C:\Users\UserName\AppData\Roaming\Unitrunker\R00000002".
3. Install Trunking Recorder
4. Start Trunking Recorder.
5. Configure first copy of Trunking Recorder per normal, enable Web Server if wanted, select correct Audio line, etc., but change the Unitrunker data folder location to the above Reciever folder. Example "C:\Users\UserName\AppData\Roaming\Unitrunker\R00000002". Leave Data output folder the same or change to your liking, but use this same path for ALL copies on Trunking Recorder!
6. For each additional voice receiver, repeat step 2. Then, find the install location of Trunking Recorder. For Windows 7, default location is "C:\Program Files (x86)\Trunking Recorder". Copy and paste that folder, and rename it to something more conventient like "Trunking Recorder-2". So, following the Windows 7 example, the complete path will now be "C:\Program Files (x86)\Trunking Recorder-2".
7. Start the Trunking Recorder binary in the newly created folder from step 6.
8. Configure the new copy of Trunking Recorder with the correct audio device, but disable the web server (the first copy runs that) and change the Unitrunker data location to the next applicable Voice Receiver. Use the same Data output folder from the first copy of Trunking Recorder.
9. Repeat steps 6-8 for each additional Voice Receiver. If setup correctly, each copy will monitor individual Voice Receiver folders created by Unitrunker, and save captured audio to the same Trunking Recorder data folder. Then, simple browse the web server created by the first copy of Trunking Recorder to view all the data!
10. Make sure each copy of Trunking Recorder is open and recording.
11. Probably a good idea to create new shortcuts to all the different copies of Trunking Scanner and place them on your desktop. Each indiviual copy has to be running and recording for everything to work.

Enjoy!
[Dreinhold]:https://github.com/dreinhold/UniLogger
[UniLogger 1.2]:http://www.scannerbox.us/TrunkingRecorder/UniLogger1.2.0.0.zip
[Trunking Recorder]:http://www.scannerbox.us/TrunkingRecorder/
[UniTrunker]:http://www.unitrunker.com
[Visual Studio 2012 Update 4]:https://www.microsoft.com/en-us/download/details.aspx?id=30679
[DSDPlus]:http://www.dsdplus.com
