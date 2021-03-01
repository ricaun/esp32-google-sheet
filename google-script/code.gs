// ------------------------------------------------------------- //

// code.gs
// This code is used to post csv data to the sheet
// 16-12-2019
// Created by ricaun

// ------------------------------------------------------------- //
// ------------------------ POST ------------------------------- //
// ------------------------------------------------------------- //

function doPost(e) {
  
  if (e == undefined) return ContentService.createTextOutput("");
  
  var content = e.postData.contents;
  
  if (content == undefined) return ContentService.createTextOutput("");

  var doc = addLine(content);
  
  var text = "POST: " + content;

  return ContentService.createTextOutput(text);
}

// ------------------------------------------------------------- //
// ------------------------ GET -------------------------------- //
// ------------------------------------------------------------- //

function doGet(e){
  return ContentService.createTextOutput(getSpreadSheetName());
}

// ------------------------------------------------------------- //
// ------------------------------------------------------------- //
// ------------------------------------------------------------- //
// Format
// ; => new line
// | => next value
// ------------------------------------------------------------- //

function addLine(content)
{
  var array = content.split(";");
  
  var time = new Date();
  var mac = array.shift();
  var size = array.length;
  
  for(var i = 0; i< size; i++)
  {
    var valores = array[i].split("|");

    var values = [];
    var timeValue = getTimeSecond(time, 1+i-size);
    
    values.push(timeValue);
    values.push(mac);

    for (var j = 0; j < valores.length; j++)
    {
      var valor = str2float(valores[j]);
      values.push(valor);
    }

    addArrayBefore(values);  
  }
}

function addArray(array)
{
  var ss = SpreadsheetApp.getActive();
  var sheet = ss.getActiveSheet();
  var line = sheet.getLastRow() + 1;
  var newRange = sheet.getRange(line, 1, 1, array.length);
  sheet.getRange(1, 1, 1, array.length).copyTo(newRange);
  newRange.setValues([array]);
}

function addArrayBefore(array)
{
  var ss = SpreadsheetApp.getActive();
  var sheet = ss.getActiveSheet();
  sheet.insertRowBefore(2);
  var line = 2;
  var newRange = sheet.getRange(line, 1, 1, array.length);
  sheet.getRange(1, 1, 1, array.length).copyTo(newRange);
  newRange.setValues([array]);
}

function getTimeSecond(time, second)
{
  var ss = SpreadsheetApp.getActive();
  var spreadsheetTimezone = ss.getSpreadsheetTimeZone();
  var now = Utilities.formatDate(new Date(time.getTime() + second*1000), spreadsheetTimezone,'dd/MM/yyyy HH:mm:ss');
  return now;
}

function getTime()
{
  var ss = SpreadsheetApp.getActive();
  var spreadsheetTimezone = ss.getSpreadsheetTimeZone();
  var now = Utilities.formatDate(new Date(), spreadsheetTimezone,'dd/MM/yyyy HH:mm:ss');
  return now;
}

function getSpreadSheetName()
{
  var ss = SpreadsheetApp.getActive();
  return ss.getName();
}

// ------------------------------------------------------------- //
// ------------------------------------------------------------- //
// ------------------------------------------------------------- //

function str2float(str)
{
  return parseFloat(str.replace(',','.'));
}

// ------------------------------------------------------------- //
// ------------------------------------------------------------- //
// ------------------------------------------------------------- //
