//----------------------------------------//
//  google.ino
//
//  created 16/12/2019
//  by Luiz H. Cassettari
//----------------------------------------//

#include <HTTPClient.h>

String post_google(String path, String body)
{
  if (path == "") return "";

  HTTPClient http;

  String payload = "";

  Serial.print("[HTTP] begin...\n");

  http.begin(path);
  http.setTimeout(10000);
  http.setReuse(true);

  const char * headerkeys[] = {"Location"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  http.collectHeaders(headerkeys, headerkeyssize);

  Serial.printf("[HTTP] POST \n");

  int httpCode = http.POST(body);

  String location = http.header((size_t) 0);

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    payload = "";
  }

  http.end();

  if (httpCode == HTTP_CODE_FOUND)
  {
    payload = get_google(location);
  }

  return payload;
}

String get_google(String path)
{
  if (path == "") return "";

  String payload = "";

  HTTPClient http;

  http.begin(path);
  http.setReuse(true);
  http.setTimeout(5000);

  const char * headerkeys[] = {"Location"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  http.collectHeaders(headerkeys, headerkeyssize);

  int httpCode = http.GET();

  String location = http.header((size_t) 0);

  Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode == HTTP_CODE_OK)
  {
    payload = http.getString();
  }

  http.end();

  if (httpCode == HTTP_CODE_FOUND)
  {
    payload = get_google(location);
  }

  return payload;
}
