# MSXML
XML Operation using C++ and MSXML

  **Step 1 :** Import msxml.dll to your application. for this application I have imported msxml6.dll.
  
  **Step 2 :** Before calling/using any of the msxml function you need to call the function coinitialize(NULL).
  
  **Step 3 :** create Object of Interface IXMLDOMDocumnet2Ptr and initialize with **(__uuid(MSXML2::DOMDocument60)**.
  
  **Step 4 :** Create object of class **\_variant_t** by passing fileName with complete path.
  
  **Step 5 :** Load the xml file in raw format using function **raw_load()**.
  
  **Step 6 :** Create object of interface **MSXML2::IXMLDOMNodePtr** call the function **selectSingleNode()** by passing appropriate tag.
  
  **Step 7 :** Create object of interface **MSXML2::IXMLDOMNamedNodeMapPtr** and initialize it with node Attribute.
  
  **Step 8 :** using object of interface **MSXML2::IXMLDOMNamedNodeMapPtr** call **getNamedItem()** by passing tag name of the current located Node.
  
  **Step 9 :** create a variable of type **\_bstr_t** to receive the nodeValue, and then using **copy()** function we can get the data in wstring format.  
 
