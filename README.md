# Hardlight-UE4-Plugin
The UE4 Hardlight suit plugin source

Requirements & Limitations
	Project
		You need a <ProjectDir>/Content/Haptics folder. Move the Plugin/Content/Haptics to <ProjectDir>/Content/Haptics.
    If there is no detected Content/Haptics folder, it will crash the project (an annoying and temporary problem)
	Packaged
		You need a <PackagedGame>/<ProjectDir>/Content/Haptics folder. Copy your project's Content/Haptic folder into the packaged game directories.
		You need to manually copy the folders with the DLLs. Copy the Win32 and Win64 folders from <ProjectDir>Plugins/HapticSuit/Source/ThirdParty/Lib/ to <PackagedGame>/<ProjectDir>/Binaries/
	Service
		The Service must be running and enabled. Download it from https://github.com/NullSpaceVR/NullSpace-Chimera-SDK
		If you do not have access, fill out https://goo.gl/forms/Gv3JMLS0YkS9zsHt2

If you have questions or comments email devs@nullspacevr.com and start the email title with [UNREAL]

Thank you for your time and patience,
-Jonathan Palmer
