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

#include <libxml/tree.h>

#include "../queue/queue.h"

struct _xml_document;
typedef struct _xml_document *XmlDocument;

struct _xml_element;
typedef struct _xml_element *XmlElement;

/*
   setup_xml() Sets up the XML module.
      PRE:  None.
      POST: XML module configured and ready for use.
            cleanup_xml() should be called when the XML module is
                           no longer required by the client.
*/
void setup_xml(void);


/*
   cleanup_xml() Cleans up the XML module.
      PRE:  None.
      POST: Cleans up the XML module. The XML module will not work unless
            another call is made to setup_xml().
*/
void cleanup_xml(void);

/*
   load_xml_document(filename) Loads filename and parses the XML document.
      PRE:  XML module has been setup.
      POST: A pointer to the document, or NULL if an error occured.
            Memory must be free by calling free_xml_document(doc).
*/
XmlDocument load_xml_document(const char *filename);

/*
   free_xml_document(doc) Frees the document.
      PRE:  XML module has been setup.
      POST: doc is freed and no longer valid.
*/
void free_xml_document(XmlDocument doc);

XmlElement xml_document_root_node(XmlDocument doc);

Queue xml_element_children(XmlElement element);

//const char *xml_element_type(XmlElement element);
const char *xml_element_name(XmlElement element);
const char *xml_element_content(XmlElement element);

void xml_traverse_elements(XmlElement element, void (*fn)(XmlElement element));

void free_xml_element(XmlElement element);
