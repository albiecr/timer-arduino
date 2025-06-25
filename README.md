<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&height=100&color=FF78CB&section=header&reversal=false&descAlign=22&descAlignY=42"/>

<div align="center">
  <a href="https://github.com/albiecr">
    <img src="https://readme-typing-svg.herokuapp.com?font=Sour+Gummy&size=40&pause=100&color=EF82F7&width=500&height=60&lines=Arduino+Timer+Project" alt="Typing SVG" />
  </a>
</div>

<img align="right" height="300" src="https://github.com/user-attachments/assets/fd55a292-b980-4a5c-82e3-9b972d627255" />

<h2>📜 Description</h2>

Simple timer system created using Arduino UNO, with countdown functionality, pause/resume, LED and buzzer alerts, and LCD display for user feedback.

<h2>✨ Features</h2>

• Countdown timer with configurable time  
• Add 30 seconds increments before starting  
• Pause and resume functionality  
• LCD 16x2 (I2C) real-time display  
• Green LED indicates countdown is running  
• Red LED + Buzzer alerts when timer ends  
• Button debounce handling  
• Serial Monitor logging (optional)  

<h2>📋 Requirements</h2>

• Arduino UNO  
• LCD 16x2 with I2C module  
• 3x push buttons  
• 1x Buzzer  
• 1x Green LED and 1x Red LED  
• Resistors (220Ω for LEDs, optional 10kΩ for pull-downs)  
• Breadboard and jumper wires  
• Arduino IDE  

<h2>⚙️ Circuit Schematic</h2>

You can view the schematic in the file:  
📄 [timer-schematic view.pdf](https://github.com/albiecr/timer-arduino/blob/main/timer-schematic%20view.pdf)

The image below shows the circuit assembled on the Tinkercad platform:

![Image](https://github.com/user-attachments/assets/d7bb27b0-3718-4b67-b792-dc6b312b7610)

<h2>🔌 Pin Connections</h2>

| Component         | Arduino Pin |
|------------------|-------------|
| Start Button      | D2          |
| +30s Button       | D3          |
| Stop Button       | D4          |
| Green LED         | D5          |
| Red LED           | D6          |
| Buzzer            | D7          |
| LCD SDA           | A4          |
| LCD SCL           | A5          |

> All buttons are connected to GND on one side and use `INPUT_PULLUP` on the Arduino.

<h2>🚀 Upload & Usage</h2>

1. Connect components following the schematic.  
2. Open the `.ino` file in Arduino IDE.  
3. Select the correct board (Arduino UNO) and port.  
4. Upload the code.  
5. Interact with the buttons:
   - Press **+30s** to increase the timer
   - Press **Start** to begin
   - Press **Stop** to pause
   - Press **Start** again to resume

<h2>🏗️ Code Structure</h2>

```cpp
setup()         // Initializes LCD, pins, and state
loop()          // Handles button presses and countdown logic
startTimer()    // Starts countdown from configured time
resumeTimer()   // Resumes countdown from paused time
stopTimer()     // Pauses countdown and stores time left
endTimer()      // Ends countdown, triggers buzzer/LED
updateDisplay() // Shows time set before starting
```
<h2>📄 License</h2> 

This project is licensed under the MIT License — see the [LICENSE](https://github.com/albiecr/timer-arduino/blob/main/LICENSE) file for details.


<h2>✉️ Contact</h2>
Albertina Rodrigues - albertinacrodrigues@gmail.com <br>
Project Link: https://github.com/albiecr/arduino-timer-project

<h2>🔮 Future Improvements</h2> <h4>1. Hardware:</h4> • Add rotary encoder for time configuration <br> 
• RTC (Real-Time Clock) integration <br> 
• OLED support 
<h4>2. Software:</h4> 
• EEPROM time save <br> 
• Multiple timer modes (count up / intervals) <br> 
• Web interface via ESP8266 

<h2>🤝 Contributing </h2>
<img align = "right" height = "300" src = "https://github.com/user-attachments/assets/3b30fe86-71ff-400d-92eb-1f66f1d9ca4d"/>
Contributions are welcome! Please open an issue or submit a pull request. <br><br>

1. Fork the project <br><br>
2. Create your feature branch <pre><code class="language-bash">git checkout -b feature/AmazingFeature</code></pre>
3. Commit your changes <pre><code class="language-bash">git commit -m 'Add some AmazingFeature'</code></pre>
4. Push to the branch <pre><code class="language-bash">git push origin feature/AmazingFeature</code></pre>
5. Open a pull request
