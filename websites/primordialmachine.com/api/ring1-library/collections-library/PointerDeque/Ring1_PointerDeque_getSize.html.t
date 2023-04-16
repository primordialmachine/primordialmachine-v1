@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_pointerdeque_getsize">Ring1_PointerDeque_getSize</h3>
<p>Get the size of a pointer deque.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_PointerDeque_getSize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int64_t *size,
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerDeque *pointerDeque<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function gets the size of a pointer deque.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">size</code></dt><dd>A pointer to a <code class="inline">int64_t</code> variable.
  If this function succeeds, that variable is assigned the size.</dd>
  <dt><code class="inline">pointerDeque</code></dt><dd>A pointer to the pointer deque.</dd>
</dl>

<h4>Return value</h4>
<p><code class="inline">Ring1_Result_Success</code> on success. <code class="inline">Ring1_Result_Failure</code> on failure.</p>

@(>"./_footer.html.t")
