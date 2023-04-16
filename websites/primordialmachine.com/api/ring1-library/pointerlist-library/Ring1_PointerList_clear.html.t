@{title = "Ring 1 :: Pointer List Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_pointerlist_clear">Ring1_PointerList_clear</h2>
<p>Clear this pointer list.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_PointerList_clear<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerList *self<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function clears this pointer list.
If a "removed" callback is associated with the pointer list object,
then this function will be invoked on each removed pointer.
This function stops removing pointers as soon as a "removed" callback returns an error.
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

@(>"./_footer.html.t")
