 #!/usr/bin/env bash

# replace this with your server path
ServerFirmwarePath="/Users/mattl/Documents/Development/HackReactor/thesis/server/resource/firmware"

if [ ! -d "$ServerFirmwarePath" ]
then
  ls "$ServerFirmwarePath"
  echo "Err: please update server firmware path in the script file"
  exit 1
fi

# Widget build script template
build_widget() {
  WidgetName=$1

  if [ ! -d "$WidgetName" ]
  then
    echo "Err: Widget directory not found: $WidgetName"
    exit 1
  fi

  if [ ! -d "$WidgetName/build" ]
  then
    echo "No build dir exists, creating one"
    mkdir "$WidgetName/build"
  fi

  echo "Running particle build script: $WidgetName"

  particle compile photon "$WidgetName" --saveTo "$WidgetName/build/$WidgetName.bin"
  echo "Copying to server folder: $WidgetName.bin"
  cp "$WidgetName/build/$WidgetName.bin" "$ServerFirmwarePath"

  # echo results path
  echo "$ServerFirmwarePath"
  ls "$ServerFirmwarePath"

}

if [[ $# == 0 ]]
then
  # set all widgets for compile
  build_args=("DateTimeWeatherWidget" "StocksWidget") # ADD NEW WIDGETS HERE
  for arg in "${build_args[@]}"
  do
    build_widget "$arg"
  done
else
  for arg in "$@"
  do
    build_widget "$arg"
  done
fi