@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_removedcallback">Ring1_RemovedCallback</h3>
<p>The type of a "removed" callback function for collections.</p>
<p><code class="block">
typedef void (Ring1_RemovedCallback)(void* element);
</code></p>

<p>
A function of this type can be associated with certain collections.
The function is invoked before an element is added to a collection.
A pointer to the element is passed to the function as its single argument.
A "removed" callback function must not mutate the collection it is associated with.
One can safely define a "removed" callback with a more specialized pointer type than <code class="inline">void</code>.
</p>

<h4>Parameter variables</h4>
<dl>
  <dt><code class="inline">element</code></dt><dd>A pointer to the element.</dd>
</dl>

@(>"./_footer.html.t")
