# MSXML 
XML Operation using C++ and MSXML

 [1. Basic Operation](#1-basic-operation)
 
 [2. Reading Value of Attribute](#2-reading-value-of-attribute)
 
 [3. Reading List of Data](#3-reading-list-of-data)
 
 [4. Writing XML file](#4-writing-xml-file)
 
 

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
<pre><code>
  bool GetAttribute(const MSXML2::IXMLDOMNodePtr &nodePtr,const std::wstring &Attrdata, std::wstring &Attrval)
  {
	MSXML2::IXMLDOMNamedNodeMapPtr nodeMapPtr;
	nodeMapPtr = nodePtr->attributes;
	_bstr_t  value;
	MSXML2::IXMLDOMNodePtr node = nodeMapPtr->getNamedItem(Attrdata.data());
	if (node == nullptr)
	{
		return FALSE;
	}
	value = node->nodeValue;
	Attrval = value.copy(FALSE);
	return true;
  }
</code></pre>
## 3. Reading List of Data ##

  **Step 1 :** Create Object of interface **MSXML2::IXMLDOMNodeListPtr** and initialize with **nodeptr->childNodes** where **nodeptr** is object of **MSXML2::IXMLDOMNodePtr** initialized with **SelectSingleNode()** function.
  Directly one can use function **GetChilds()**.

<pre><code>
 std::vector&lt;MSXML2::IXMLDOMNodePtr&gt; GetChilds(const MSXML2::IXMLDOMNodePtr &nodePtr)
 {
	std::vector&lt;MSXML2::IXMLDOMNodePtr&gt; vctr;
	MSXML2::IXMLDOMNodeListPtr lstPtr = nodePtr->childNodes;
	if (lstPtr)
	{
		int count = lstPtr->length;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				MSXML2::IXMLDOMNodePtr nodePtr = lstPtr->item[i];
				vctr.push_back(nodePtr);
			}
		}
	}
	return vctr;
 }
</code></pre>
 ## 4. Writing XML file ##
 
  **Step 1 :** Create object of interface **MSXML2::IXMLDOMDocument2Ptr**.
  
  **Step 2 :** Create the COM DOM object.
<pre><code>
  spDocOutput.CreateInstance(__uuidof(MSXML2::DOMDocument60));
  //spDocOutput is object of type MSXML2::IXMLDOMDocument2Ptr
</code></pre>
  **Step 3 :** Create Processing Instruction object of interface **MSXML2::IXMLDOMProcessingInstructionPtr**.
<pre><code>
  spXMLDecl = spDocOutput->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"euc-kr\" standalone=\"yes\" ");
  //spXMLDecl is object of type MSXML2::IXMLDOMProcessingInstructionPtr
  spDocOutput->appendChild(spXMLDecl);
</code></pre>
  **Step 4 :** create DOM object of Element Pointer of interface **MSXML2::IXMLDOMElementPtr**.
<pre><code>
   spElemRoot = spDocOutput->createElement("AOI");
   //spElemRoot is object of type MSXML2::IXMLDOMElementPtr
   spDocOutput->appendChild(spElemRoot);
</code></pre>
  **Step 5 :** To add element and its value call the function **AddAttrToXml()**.
<pre><code>
bool AddAttrToXml(const MSXML2::IXMLDOMElementPtr spElem, std::wstring attrData, std::wstring attrVal)
{
	VARIANT varVal;
	VariantInit(&varVal);
	varVal.vt = VT_BSTR;
	// given std::wstring ws
	//NodeName
	varVal.bstrVal = SysAllocStringLen(attrVal.data(), (UINT)attrVal.size());
	HRESULT hr = spElem->setAttribute(attrData.c_str(), varVal);

	SysFreeString(varVal.bstrVal);

	if (SUCCEEDED(hr))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
</code></pre>
 **Step 6 :** To save the data in XML file call the save function passing the parameter as name and path of the file as shown below.
 <pre><code>
   spDocOutput->save(wstrFileName.c_str());
 </code></pre>
