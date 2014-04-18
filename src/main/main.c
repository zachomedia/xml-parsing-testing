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

#include "../xml/xml.h"

void print_element(XmlElement element)
{
   printf("Element\n\tname: %s\n\tvalue: %s\n", xml_element_name(element),
                                                xml_element_content(element));
}// End of print_element

int main(void)
{
   // Setup modules
   setup_xml();

   // Do stuff
   XmlDocument doc = load_xml_document("test.xml");
   XmlElement root = xml_document_root_node(doc);

   Queue alerts = xml_element_children(root);

   while(!queue_empty(alerts))
   {
      XmlElement alert = queue_dequeue(alerts);
      Queue alert_info = xml_element_children(alert);

      while(!queue_empty(alert_info))
      {
         XmlElement info = queue_dequeue(alert_info);
         print_element(info);

         free_xml_element(info);
      }// End of while

      destroy_queue(alert_info);

      //xml_traverse_elements(alert, print_element);

      free_xml_element(alert);
   }// End of while

   destroy_queue(alerts);

   /*XmlElement *alerts = xml_element_children(root);

   for (XmlElement el = alerts; el; ++el)
   {
      xml_traverse_elements(el, print_element);
   }// End of for*/

   free_xml_element(root);
   free_xml_document(doc);

   // Cleanup modules
   cleanup_xml();
}// End of main method
