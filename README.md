# MSXML
XML Operation using C++ and MSXML

  **Step 1 :** Import msxml.dll to your application. for this application I have imported msxml6.dll.
  
  **Step 2 :** Before calling/using any of the msxml function you need to call the function coinitialize(NULL).
  
  **Step 3 :** create Object of Interface IXMLDOMDocumnet2Ptr and initialize with **(__uuid(MSXML2::DOMDocument60)**.
  
  **Step 4 :** Create object of class **\_variant_t** by passing fileName with complete path.
 
