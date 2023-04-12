@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_isequaltocallback">Ring1_IsEqualToCallback</h3>
<p>The type of an "equal" callback function for collections.</p>
<p><code class="block">
typedef Ring1_Result (Ring1_Collection_IsEqualToCallback)(bool *result, void* first, void *second);
</code></p>

<p>
A function of this type can be associated with certain collections.
The function will be invoked by the associated collection when elements need to be compared for equality.
The pointers to the elements are passed as the 2nd and 3rd argument to the function,
a pointer to the variable to assign the result to as its 1st argument.
An "isEqualTo" callback function must not mutate the associated pointer collection.
One can safely define an "isEqualTo" callback with a more specialized pointer types than <code class="inline">void</code>.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">result</code></dt><dd>A pointer to the <code class="inline">bool</code> variable.</dd>
  <dt><code class="inline">left</code></dt><dd>A pointer to the first element.</dd>
  <dt><code class="inline">right</code></dt><dd>A pointer to the second element.</dd>
</dl>

<h4>Success</h4>
<p><code class="inline">*result</code> is assigned <code class="inline">true</code> if the elements are equal.
Otherwise it is assigned <code class="inline">false</code>.</p>

<h4>Failure</h4>
<p><code class="inline">result</code> is not dereferenced.</p>

<h4>Return value</h4>
<p><code class="inline">Ring1_Result_Success</code> on success. <code class="inline">Ring1_Result_Failure</code> on failure.</p>

@(>"./_footer.html.t")
