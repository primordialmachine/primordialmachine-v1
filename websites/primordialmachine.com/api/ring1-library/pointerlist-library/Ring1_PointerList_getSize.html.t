@{title = "Ring 1 :: Pointer List Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_pointerlist_getsize">Ring1_PointerList_getSize</h2>
<p>Get the size of this pointer list.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_PointerList_getSize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int64_t* result,
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerList* self<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function gets the size of this pointer list.
</p>

<h3>Parameter variables</h3>
<dl>
  <dt><code class="inline">result</code></dt>
  <dd>
  A pointer to a <code class="inline">int64_t</code> variable.
  If this function succeeds, that variable is assigned the size.
  </dd>
  
  <dt><code class="inline">self</code></dt>
  <dd>
  A pointer to this pointer list.
  </dd>
</dl>

<h3>Return Values</h3>
<p>
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Success</a></code> on success,
<code class="inline"><a href="@(baseurl)api/ring1-library/result-library/result-codes">Ring1_Result_Failure</a></code> on failure.
</p>

@(>"./_footer.html.t")
