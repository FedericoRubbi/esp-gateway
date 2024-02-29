Here are reported the steps to install and use `screen` for reading serial data on Linux-based systems.

## Installation

First, install `screen` running.
```bash
sudo apt update
sudo apt install screen
```

## Listing Serial Ports

Before you start `screen`, you need to identify the serial port your device is connected to:

1. Connect your device.
2. Open a terminal and list the available serial devices:

```bash
ls /dev/ttyUSB* /dev/ttyS*
```

Look for devices named `/dev/ttyUSB0`, `/dev/ttyS0`, or similar. The exact name depends on your device and how it's connected.

## Read Serial Data

Once you've identified your device's serial port, you can use `screen` to start reading data from it. Replace `/dev/ttyUSB0` with the correct serial port identifier for your device.

```bash
screen /dev/ttyUSB0 115200
```

## Detaching and Exiting Screen

- To **detach** from a `screen` session (leaving it running in the background), press `Ctrl-A` followed by `D`.
- To **exit** a `screen` session (terminating it), type `exit` from within the session or press `Ctrl-A` followed by `K`, then confirm with `y`.

## Checking Running Screen Sessions

To see if any `screen` sessions are running in the background:

```bash
screen -ls
```

## Terminating a Screen Session

If you need to terminate a background `screen` session, first find its session ID with `screen -ls`, then use:

```bash
screen -X -S sessionID quit
```

Replace `sessionID` with the actual ID of the session you wish to terminate.