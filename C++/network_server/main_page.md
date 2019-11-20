\mainpage Project main page

	\section intro_sec Introduction
	The project realize TCP/IP server module for IPv4 and IPv6 familly.
	This module service multi connections and can waiting for new connection in another thread.

	\section install_sec Installation
	
		\subsection step1 Step 1: Install tools
		Requiremnet tools:
		* cmake 3.14
		* gcc GNU 7.4.0
		* g++ GNU 7.4.0
		
		\subsection step2 Step 2: Build project
		Create build folder and run cmake command: `cmake -B<build_folder> -H<project_folder>`.
		* <build_folder> - folder for binary file 
		* <project_folder> - where is project folder
		
		Go to build folder and run make command: `make`. 
		That complile project and create binary application with name `network_server`. 

	\section details_sec Details
	Network server service TCP/IP socket by `Server_Socket` class. 
	All incoming client connections are save to list in main manager class `Network_Server` 
	as `Server_Connection` object. The object contains all client connection informations.
	
	