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

#include "xml.h"

#include <stdbool.h>
#include <libxml/parser.h>

bool setup = false;

struct _xml_document
{
   xmlDocPtr doc;
};

struct _xml_element
{
   xmlNode *node;
};

// See header for details
void setup_xml(void)
{
   if (!setup)
   {
      LIBXML_TEST_VERSION

      setup = true;
   }// End of if
}// End of setup_xml method

// See header for details
void cleanup_xml(void)
{
   if (setup)
   {
      xmlCleanupParser();

      setup = false;
   }// End of if
}// End of cleanup_xml method

// See header for details
XmlDocument load_xml_document(const char *filename)
{
   if (!setup) return NULL;
   if (!filename) return NULL;

   XmlDocument doc = malloc(sizeof(struct _xml_document));
   if (!doc) return NULL;

   doc->doc = xmlReadFile(filename, NULL, 0);

   return doc;
}// End of load_xml_document method

// See header for details
void free_xml_document(XmlDocument doc)
{
   if (!doc) return;

   xmlFreeDoc(doc->doc);
   free(doc);
}// End of free_xml_document method

// See header for details
XmlElement xml_document_root_node(XmlDocument doc)
{
   if (!doc) return NULL;
   if (!doc->doc) return NULL;

   XmlElement element = malloc(sizeof(struct _xml_element));
   if (!element) return NULL;

   element->node = xmlDocGetRootElement(doc->doc);

   return element;
}// End of xml_document_root_node method

// See header for details
const char *xml_element_name(XmlElement element)
{
   if (!element) return NULL;
   if (!element->node) return NULL;

   return (char *)element->node->name;
}// End of xml_element_name method

const char *xml_element_content(XmlElement element)
{
   if (!element) return NULL;
   if (!element->node) return NULL;

   return (char *)xmlNodeGetContent(element->node);
}// End of of xml_element_content method

static XmlElement create_XmlElement(xmlNode *node)
{
   XmlElement el = malloc(sizeof(struct _xml_element));

   el->node = node;

   return el;
}

// See header for details
void xml_traverse_elements(XmlElement element, void (*fn)(XmlElement element))
{
   if (!element) return;
   if (!element->node) return;
   if (!fn) return;

   xmlNode *cur_node = NULL;
   for (cur_node = element->node; cur_node; cur_node = cur_node->next)
   {
      XmlElement el = create_XmlElement(cur_node);

      if (cur_node->type == XML_ELEMENT_NODE)
         fn(el);

      free_xml_element(el);
   }// End of for
}// End of xml_traverse_elements

void free_xml_element_void(void *element)
{
   free_xml_element((XmlElement)element);
}

// See header for details
Queue xml_element_children(XmlElement element)
{
   if (!element) return NULL;
   if (!element->node) return NULL;

   Queue children = create_queue(free_xml_element_void);
   xmlNode *cur_node = NULL;

   for (cur_node = element->node->children; cur_node; cur_node = cur_node->next)
   {
      if (cur_node->type == XML_ELEMENT_NODE)
         queue_queue(children, create_XmlElement(cur_node));
   }// End of for

   return children;
}// End of xml_element_children method

// See header for details
void free_xml_element(XmlElement element)
{
   if (!element) return;

   free(element);
}// End of free_xml_element method
