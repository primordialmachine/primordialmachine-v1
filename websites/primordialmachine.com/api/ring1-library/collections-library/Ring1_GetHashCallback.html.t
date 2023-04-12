@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_gethashcallback">Ring1_GetHashCallback</h3>
<p>The type of a "hash" callback function used by collections.</p>
<p><code class="block">
typedef Ring1_Result (Ring1_GetHashCallback)(int64_t *result, void* element);
</code></p>

<p>
A function of this type can be associated with certain collections.
The function will be invoked by the associated collection when the hash value of an element needs to be computed.
A pointer to the element is passed to the function as its 2nd argument, a pointer to the variable to assign the hash value to as its 1st argument.
A "hash" callback function must not mutate the collection.
One can safely define a "hash" callback with a more specialized pointer type than <code class="inline">void</code>.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">result</code></dt><dd>A pointer to the <code class="inline">int64_t</code> variable.</dd>
  <dt><code class="inline">key</code></dt><dd>A pointer to the element.</dd>
</dl>

<h4>Success</h4>
<p><code class="inline">*result</code> is assigned the hash value of the element.</p>

<h4>Failure</h4>
<p><code class="inline">result</code> is not dereferenced.</p>

<h4>Return value</h4>
<p><code class="inline">Ring1_Result_Success</code> on success. <code class="inline">Ring1_Result_Failure</code> on failure.</p>

@(>"./_footer.html.t")
