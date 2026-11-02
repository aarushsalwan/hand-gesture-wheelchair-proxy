# Hand-Gesture Controlled Wheelchair (Proxy Prototype)

A small-scale prototype of a wheelchair that is driven by tilting your hand. A wearable controller reads hand orientation and sends commands wirelessly to a motorised base. The base is a model car standing in for a real wheelchair, which made it possible to build and test the control system safely and cheaply.

The goal is to make mobility easier for people with paraplegia or limited hand strength, who may find a standard joystick difficult to use.

<img width="4284" height="5712" alt="IMG_1810" src="https://github.com/user-attachments/assets/787bb76d-2285-42a0-ba78-c81dd50cd403" />

https://github.com/user-attachments/assets/f9431316-5b6e-48f8-8f99-bccd712430c6
**Testing note:** On smooth floors the chair turns fully on the spot, but on carpet it turns only partly. Because it is four-wheel drive, it turns by skidding its wheels sideways (skid steering), and carpet adds a lot of friction to that sideways slide.


---

## How it works

```
 [ Hand unit ]                         [ Wheelchair proxy ]
 ESP32 + MPU6050  ── ESP-NOW (wireless) ──>  ESP32 + L298N motor driver + 4 DC motors
 + stop button                                 + status LED
```

1. **Read the hand.** An MPU6050 accelerometer on the hand unit measures how far the hand is tilted along two axes.
2. **Turn tilt into a command.** If the tilt passes a threshold (about 30°), it becomes a direction: forward, backward, left or right. Small movements are ignored, so the chair doesn't react to normal hand shake.
3. **Send it wirelessly.** Every 100 ms, the hand unit sends the command to the car using **ESP-NOW**, a direct ESP32-to-ESP32 protocol that needs no Wi-Fi router.
4. **Drive the motors.** The car's ESP32 receives the command and switches the motor driver to run the left and right wheels in the right direction. To turn, the left and right sides spin in opposite directions, so the chair can turn on the spot.

**Testing note:** On smooth floors the chair turns fully on the spot, but on carpet it turns only partly. Because it is four-wheel drive, it turns by skidding its wheels sideways, and carpet adds a lot of friction to that slide.

## Controls

| Hand movement      | Wheelchair action |
|--------------------|-------------------|
| Tilt forward       | Move forward      |
| Tilt backward      | Move backward     |
| Tilt left          | Turn left         |
| Tilt right         | Turn right        |
| Hold hand level    | Stop              |
| Press the button   | Emergency stop on/off (LED lights up while stopped) |

The emergency stop is a toggle, so the user can lock the chair in place without having to hold their hand perfectly still.

## Hardware

**Hand unit**
- ESP32 dev board
- MPU6050 accelerometer/gyroscope (I²C on GPIO 21/22)
- Push button (GPIO 4)
- Battery

**Wheelchair proxy**
- ESP32 dev board
- L298N motor driver (IN1–IN4 on GPIO 14, 27, 26, 25)
- 4 DC geared motors + wheels (four-wheel drive)
- Status LED (GPIO 2)
- Battery pack
- Powerbank

## Repository layout

```
final_transmitter/   Code for the hand unit
final_receiver/      Code for the wheelchair proxy
development/         Test sketches written while building the project
```

## Development process

The `development/` folder shows how the project was built up one piece at a time:

1. **Sensors:** tested a flex sensor (`flexsensor_input`), then switched to the MPU6050 (`I2Cdevices_search`, `basic_readings_mpu6050`) because tilt gave clearer, more reliable directions than finger bending.
2. **Wireless link:** found each board's MAC address (`esp32mac_address_hand`, `esp32mac_address_car`) and got ESP-NOW messages passing between them (`espnow`, `espnow_car`).
3. **Motors:** tested motors individually and in pairs (`motor12`, `motor34`, `full_motor`), tried speed control with PWM (`motorcode_3`), and tried a two-wheel-drive layout with a caster (`2wd`, `caster`, `motor_forward`) before settling on four-wheel drive.
4. **Integration:** combined everything into transmitter/receiver code (`transmitter_hand`, `receiver_car`), then added the stop button and status LED in the final version.

## Running it yourself

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and add ESP32 board support.
2. Install the **Adafruit MPU6050** and **Adafruit Unified Sensor** libraries.
3. Upload `development/esp32mac_address_car` to the car's ESP32 and note the MAC address it prints.
4. Put that address into `broadcastAddress[]` in `final_transmitter.ino`.
5. Upload `final_transmitter` to the hand unit and `final_receiver` to the car.

## Next steps

- **Proportional speed:** use PWM so a bigger tilt means a faster speed, instead of just on or off.
- **Signal-loss safety:** stop the chair automatically if no command arrives for a short time.
- **Calibration:** let each user set their own neutral hand position and tilt thresholds.
- **Better turning on carpet:** use higher-torque motors or a higher-voltage battery so the chair can turn fully on any surface.

## License

MIT. See [LICENSE](LICENSE).
