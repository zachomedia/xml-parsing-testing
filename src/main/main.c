/*
   The MIT License (MIT)

   Copyright (c) 2014 Zachary Seguin

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../xml/xml.h"

struct Alert
{
   char *summary;
   char *description;
   char *location;
};
typedef struct Alert *Alert;

bool str_equals(const char *a, const char *b)
{
   return strcmp(a, b) == 0;
}

Alert get_alert(XmlElement xml_alert)
{
   Alert alert = malloc(sizeof(struct Alert));
   Queue alert_info = xml_element_children(xml_alert);

   while (!queue_empty(alert_info))
   {
      XmlElement el = queue_dequeue(alert_info);
      const char *element = xml_element_name(el);

      if (str_equals(element, "summary")) {
         alert->summary = strdup(xml_element_content(el));
      } else if (str_equals(element, "description")) {
         alert->description = strdup(xml_element_content(el));
      } else if (str_equals(element, "location")) {
         alert->location = strdup(xml_element_content(el));
      }

      free_xml_element(el);
   }

   destroy_queue(alert_info);

   return alert;
}// End of get_alert method

void destroy_alert(void *ptr)
{
   if (!ptr) return;

   Alert alert = ptr;

   free(alert->summary);
   free(alert->description);
   free(alert->location);

   free(alert);
}

/*
   get_alerts(filename) Loads the alerts from file.
*/
Queue get_alerts(const char *filename)
{
   XmlDocument doc = load_xml_document(filename);
   XmlElement root = xml_document_root_node(doc);

   Queue xml_alerts = xml_element_children(root);
   Queue alerts = create_queue(destroy_alert);

   while (!queue_empty(xml_alerts))
   {
      XmlElement el_alert = queue_dequeue(xml_alerts);
      queue_queue(alerts, get_alert(el_alert));
      free_xml_element(el_alert);
   }// End of while

   destroy_queue(xml_alerts);

   return alerts;
}// End of get_alerts method

int main(void)
{
   // Setup modules
   setup_xml();

   Queue alerts = get_alerts("test.xml");

   while(!queue_empty(alerts))
   {
      Alert alert = queue_dequeue(alerts);
      printf("%s\n", alert->summary);
      printf("  For: %s\n", alert->location);
      printf("  %s\n", alert->description);
   }// End of while

   destroy_queue(alerts);

   // Cleanup modules
   cleanup_xml();
}// End of main method
