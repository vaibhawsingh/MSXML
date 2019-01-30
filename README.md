# MSXML 
XML Operation using C++ and MSXML

 [1. Basic Operation](#1-basic-operation)
 
 [2. Reading Value of Attribute](#2-reading-value-of-attribute)
 
 [3. Reading List of Data](#3-reading-list-of-data)
 
 

--------------------------------------------------------------------------------------------------------------------------------

 ## 1. Basic Operation ##
 
  **Step 1 :** Import msxml.dll to your application. for this application I have imported msxml6.dll.
  
  **Step 2 :** Before calling/using any of the msxml function you need to call the function **coinitialize(NULL)**.
  
  **Step 3 :** create Object of Interface IXMLDOMDocumnet2Ptr and initialize with **(__uuid(MSXML2::DOMDocument60)**.
  <pre><code>
   MSXML2::IXMLDOMDocument2Ptr  pDocument = MSXML2::IXMLDOMDocument2Ptr(__uuidof(MSXML2::DOMDocument60));
  </code></pre>
  
  **Step 4 :** Create object of class **\_variant_t** by passing fileName with complete path.
  
  **Step 5 :** Load the xml file in raw format using function **raw_load()**.
  
  **Step 6 :** Create object of interface **MSXML2::IXMLDOMNodePtr** call the function **selectSingleNode()** by passing appropriate tag.
  
  ## 2. Reading Value of Attribute ##
  
  **Step 1 :** Create object of interface **MSXML2::IXMLDOMNamedNodeMapPtr** and initialize it with node Attribute.
  
  **Step 2 :** using object of interface **MSXML2::IXMLDOMNamedNodeMapPtr** call **getNamedItem()** by passing tag name of the current located Node.
  
  **Step 3 :** create a variable of type **\_bstr_t** to receive the nodeValue, and then using **copy()** function we can get the data in wstring format.
  
## 3. Reading List of Data ##

  **Step 1 :** Create Object of interface **MSXML2::IXMLDOMNodeListPtr** and initialize with **nodeptr->childNodes** where **nodeptr** is object of **MSXML2::IXMLDOMNodePtr** initialized with **SelectSingleNode()** function.
  Directly one can use function **GetChilds()**.

<pre><code>
 std::vector<MSXML2::IXMLDOMNodePtr> GetChilds(const MSXML2::IXMLDOMNodePtr &nodeptr)
{
	std::vector<MSXML2::IXMLDOMNodePtr> vctr;
	MSXML2::IXMLDOMNodeListPtr lstPtr = nodeptr->childNodes;
	if (lstPtr)
	{
		int count = lstPtr->length;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				MSXML2::IXMLDOMNodePtr nodeptr = lstPtr->item[i];
				vctr.push_back(nodeptr);
			}
		}
	}
	return vctr;
}
</code></pre>
