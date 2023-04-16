@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_addedcallback">Ring1_AddedCallback</h3>
<p>The type of an "added" callback function for collections.</p>
<p><code class="block">
typedef void (Ring1_AddedCallback)(void* element);
</code></p>

<p>
A function of this type can be associated with certain collections.
The function is invoked before an element is added to a collection.
A pointer to the element is passed to the function as its single argument.
An "added" callback function must not mutate the collection it is associated with.
One can safely define an "added" callback with a more specialized pointer type than <code class="inline">void</code>.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">element</code></dt><dd>A pointer to the element.</dd>
</dl>

@(>"./_footer.html.t")
