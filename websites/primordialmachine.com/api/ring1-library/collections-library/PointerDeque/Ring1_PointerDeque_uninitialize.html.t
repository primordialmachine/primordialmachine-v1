@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="mkx_pointerdeque_uninitialize">Mkx_PointerDeque_uninitialize</h3>
<p>Uninitialize a pointer deque.</p>
<p><code class="block">
void<br/>
Ring1_PointerDeque_uninitialize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerDeque *pointerDeque<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function uninitializes an initialized pointer deque.
The pointer deque is cleared as if <code class="inline">Mkx_PointerDeque_clear</code> was invoked on the pointer deque.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">pointerDeque</code></dt><dd>A pointer to the pointer deque.</dd>
</dl>

@(>"./_footer.html.t")
