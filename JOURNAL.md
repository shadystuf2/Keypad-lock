---
title: "Keypad lock"
author: "Nomeda"
description: "A keypad lock with user defined password and LED and OLED display"
created_at: "2026-07-21"
---

## Session 1
Started working on Version 1, which was just the ESP32 and the keypad. At first it was challenging, trying to figure out how the keypad worked. A lot of the time I was looking at others' projects to understand how it was supposed to interact with the MCU. Overall I was having trouble connecting the keypad with the ESP32 and getting frustrated.  
Version 1, 2, 3:  
<img width="752" height="718" alt="image" src="https://github.com/user-attachments/assets/38622491-f27e-4b08-a12f-7b6c28e33284" />


Time lapse: https://lapse.hackclub.com/timelapse/QORBmm-GC7Bg

## Session 2
Finished version 1 and turns out it did not work because I forgot to connect the 4th row to the MCU 🥶. Anyway, I started working on Version 2, which had more advanced logic: it prompted the user to enter the password 3 times and denied access after the third failed attempt. Or granted access if they gave the correct password. For now I hardcoded the password so that I wouldn't have to worry about too many things. At this point I was enjoying the process, reaching that flow state.

Time lapse: https://lapse.hackclub.com/timelapse/LWBgMgovsY79

## Session 3
Did Version 3 which finally had the user defined password. It was surprisingly difficult to set up since the program kept assuming that the created password was an attempt to enter the password. But I figured it out, which was very satisfying. Also, turns out multiple functions don't work in this case, so it's just one loop with a bunch of if statements. When I was looking for ideas in others' projects I saw that thay had the same issue too. Then I moved to Version 4 which was just transfering the output from terminal to an OLED display. It was quite easy, though the code was starting to look a bit messy. It gave me a headache.  
Version 4: 
<img width="1006" height="820" alt="image" src="https://github.com/user-attachments/assets/c0343b25-88ad-4ca0-b58c-eabffb619e18" />


Time lapse: https://lapse.hackclub.com/timelapse/GfME8xLR3Fx0

## Session 4
Started Version 5 where I added the 3 LED display to accompany the attempt diplay on the OLED. Another feature I added was that when access was denied it would only lock the user out for 10 seconsd and then prompt them to enter the password again. These steps were way too easy, I though they would take more time. Then I thought Version 6 would be just as fast but it wasn't. I got so confused and lost cause I added the menu and the options to either reset the password or quit. But the OLED and the whole system were just not reacting to any inputs and I couldn't figure out why for the longest time. Anyway, yey, I finished and I am very happy with the result!  
Version 5:  
<img width="914" height="818" alt="image" src="https://github.com/user-attachments/assets/6fba7d2f-bcdd-4622-ac3a-539e3f0e769e" />  
Version 6:  
<img width="1014" height="960" alt="image" src="https://github.com/user-attachments/assets/360be861-36a1-4edd-aa8b-6c8196195fde" />



Time lapse: https://lapse.hackclub.com/timelapse/2vv3uFH2Znua
