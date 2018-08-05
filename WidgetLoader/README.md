# Particle IoT Widget Loader

This is a widget loading system developed to run all of the device-side Particle Photon code for [Hardy-Bot](https://github.com/hardy-boys/hardy-bot).

Documentation for Particle development can be found here: [https://docs.particle.io/reference/firmware/photon/](https://docs.particle.io/reference/firmware/photon/)

## Widget Loader

#### ```setup()``` :  
This setup function is run on device startup, once the firmware has loaded.  Here we initialize serial connections, Particle cloud functions, initialize the display, and load the  currently selected profile from the EEPROM.

#### ```.loop()```:
This is the main loop that runs as long as the device is powered on.  In this top level loop we are just selecting which widget-specific display loop to run based on the currently active widget.

#### ```setProfile(String profileData)```:  
This function accepts profile data sent from our server and loads it onto the device EEPROM.

## Widgets

#### ```widget_setup()``` : 
Widget specifc setup.  All we do here is initialize an event listener to a particle event source for widget data events on the server.

#### ```widget_loop()``` : 
Main widget loop.  Basically just drawing to the screen based on what widget data needs to be displayed.

#### ```streamDataHandler(const char *event, const char *data)``` :
This is where Particle cloud events get handled.  A JSON buffer is allocated and used to parse the incoming data structure before updating widget variables.

## Compiling Particle projects

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
