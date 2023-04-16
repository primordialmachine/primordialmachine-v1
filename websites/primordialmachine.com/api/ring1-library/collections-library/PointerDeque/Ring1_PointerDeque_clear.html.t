@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_pointerdeque_clear">Ring1_PointerDeque_clear</h3>
<p>Clear a pointer deque.</p>
<p><code class="block">
void<br/>
Ring1_PointerDeque_clear<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerDeque *pointerDeque<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function clears a pointer deque.
If a "removed" callback is associated with the pointer deque object, then this function will be invoked on each removed pointer.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">pointerDeque</code></dt><dd>A pointer to the pointer deque.</dd>
</dl>

@(>"./_footer.html.t")
