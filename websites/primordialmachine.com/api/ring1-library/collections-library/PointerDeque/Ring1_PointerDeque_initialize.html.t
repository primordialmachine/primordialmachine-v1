@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="mkx_pointerdeque_initialize">Mkx_PointerDeque_initialize</h3>
<p>Initialize a pointer deque.</p>
<p><code class="block">
Ring1_Result<br/>
Ring1_PointerDeque_initialize<br/>
&nbsp;&nbsp;(<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_PointerDeque *pointerDeque,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;int64_t initialCapacity,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_AddedCallback *added,<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ring1_RemovedCallback *removed<br/>
&nbsp;&nbsp;)
</code></p>

<p>
This function initializes an uninitialized pointer deque with the specified capacity and the specified "added" and "removed" callbacks.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">pointerDeque</code></dt><dd>A pointer to the pointer deque.</dd>
  <dt><code class="inline">initialCapacity</code></dt><dd>The initial capacity of this pointer deque.
  If this value is negative, the default capacity <code class="inline">Ring1_PointerDeque_Capacity_Default</code> is used.
  This function fails if this value is smaller than <code class="inline">Ring1_PointerDeque_Capacity_Least</code> or
  greater than <code class="inline">Ring1_PointerDeque_Capacity_Greatest</code>.</dd>
  
  <dt><code class="inline">added</code></dt><dd>A pointer to a
  <code class="inline"><a href="@(baseurl)api/ring1-library/collections-library/Ring1_AddedCallback">
  Ring1_AddedCallback</a></code>
  function or a null pointer.
  This function is invoked on an element if it is added to the pointer deque.
  </dd>
  
  <dt><code class="inline">removed</code></dt><dd>A pointer to a
  <code class="inline"><a href="@(baseurl)api/ring1-library/collections-library/Ring1_RemovedCallback">
  Ring1_RemovedCallback
  </a></code>
  function or a null pointer.
  This function is invoked on an element if it is removed from the pointer deque.
  </dd>

</dl>

<h4>Return value</h4>
<p><code class="inline">Ring1_Result_Success</code> on success. <code class="inline">Ring1_Result_Failure</code> on failure.</p>

@(>"./_footer.html.t")
