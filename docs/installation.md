## Install instructions

### ADE based installation
   
TODO

### Installation from source

1. Install [LTTng](https://lttng.org/docs/v2.11/) to use [ros2_tracing](https://gitlab.com/micro-ROS/ros_tracing/ros2_tracing)

```bash
sudo apt-get update
sudo apt-get install lttng-tools lttng-modules-dkms liblttng-ust-dev
sudo apt-get install python3-babeltrace python3-lttng
```

2. Install ROS2 Foxy from source following [these instructions](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Development-Setup/)

3. Install dependencies

```bash
TODO
sudo apt install python3-rosdep
...
```

2. Create a workspace

```bash
mkdir -p ~/pendulum_ws/src
cd ~/pendulum_ws/src
git clone https://github.com/ros2-realtime-demo/pendulum
```

2. Install ROS dependencies using [rosdep](http://wiki.ros.org/rosdep).

```bash
source /opt/ros/foxy/setup.bash
cd ~/pendulum_ws/src
sudo rosdep init
rosdep update
rosdep install -q -y --from-paths src --ignore-src --rosdistro foxy
colcon build --merge-install # OR colcon build --symlink-install
```

3. Build workspace

```bash
cd ~/pendulum_ws
colcon build --merge-install # OR colcon build --symlink-install
```

### Crosscompile
 
 TODO
 
### Raspberry PI image

TODO