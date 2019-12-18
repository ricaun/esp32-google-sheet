# esp32-google-sheet

This project is an example of how to create and add data on a [Google Spreadsheet][1] using esp32.

The program read the analog 0 add value on a buffer and sends every 30 seconds to the [Google Spreadsheet][1].


## Wifi

* ssid - wifi ssid
* password - wifi password

## PINOS

* ANALOG_PIN - analog input
* ANALOG_TIME - read analog sample

## Google

* GOOGLE_URL - google url script
* GOOGLE_TIME - send to google sample


# Google Spreadsheet

First at all you need to make a copy of the [ESP32_Google][2] and save on your drive.

<img src="image/make-a-copy.png" width="50%">

After make a copy open the script editor.

<img src="image/script-editor.png" width="50%">

## Google Stript

You need to publish the script and deploy as web app.

<img src="image/deploy-as-web-app.png" width="50%">

Select `Execute the app as:` Me. 

Select `Who has access to the app:` Anyone, even annonymous.

<img src="image/deploy-update.png" width="50%">

Now you need to give authorization to the app, review permissions.

<img src="image/deploy-review.png" width="50%"><img src="image/deploy-review-2.png" width="50%">

Open advanced and `Go to ESP32_Google`.

<img src="image/deploy-review-3.png" width="50%">

`Allow.`

<img src="image/deploy-review-4.png" width="50%">

You deploy is ready.

<img src="image/deploy-review-5.png" width="50%">

Select the `Current web app URL` copy open a new page with the url. If everything has gone right you can see the Spreadsheet name.

Paste the `Current web app URL` on the `GOOGLE_URL` define on the esp32-google-sheet.

----
<br>
<div align="center">
<a rel="license" href="https://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
</div>

[1]: https://docs.google.com/spreadsheets/
[2]: https://docs.google.com/spreadsheets/d/11VS5QQhGR095CX6Sf-s5ar5jaTDVsAoa5uFUXeVMZts/edit?usp=sharing