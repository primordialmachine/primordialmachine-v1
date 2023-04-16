@{title = "Ring 1 :: Pointer List Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_pointerlist_initialize">Ring1_PointerList_initialize</h2>
<p>Initialize a pointer list.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_PointerList_initialize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerList *self,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_Collection_AddedCallback *added,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_Collection_RemovedCallback *removed<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function initializes an uninitialized pointer list with a pointer list's default capacity and the specified added and removed callbacks.
This pointer list must not be initialized, otherwise the behavior of this function is undefined.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">self</code></dt>
  <dd>A pointer to the pointer list.</dd>
  
  <dt><code class="inline">added</code></dt>
  <dd>
  A pointer to an
  <code class="inline"><a href="@(baseurl)api/ring1-library/collection-library/Ring1_Collection_AddedCallback">
  Ring1_Collection_AddedCallback
  </a></code>
  function or a null pointer.
  This function is invoked on an element if it is added to the pointer list.
  </dd>
  
  <dt><code class="inline">removed</code></dt>
  <dd>
  A pointer to an
  <code class="inline"><a href="@(baseurl)api/ring1-library/collection-library/Ring1_Collection_RemovedCallback">
  Ring1_Collection_RemovedCallback
  </a></code>
  function or a null pointer.
  This function is invoked on an element if it is removed from the pointer list.
  </dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

@(>"./_footer.html.t")
