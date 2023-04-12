@{title = "Ring 1 :: Pointer List Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_pointerlist_uninitialize">Ring1_PointerList_uninitialize</h2>
<p>Uninitialize this pointer list.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_PointerList_uninitialize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerList *self<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function uninitializes this pointer list.
This pointer list must be initialized, otherwise the behavior of this function is undefined.
The pointer list is cleared as if <code class="inline">Ring1_PointerList_clear</code> was invoked on the pointer list.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">self</code></dt><dd>A pointer to this pointer list.</dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>
