@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_pointerhashmap">Ring1_PointerHashMap</h3>
<p>The type of a pointer hash map.</p>
<p><code class="block">
typedef struct Ring1_PointerHashMap { ... } Ring1_PointerHashMap;<br/>
</code></p>

<p>
A hash map associates keys and values.
Both keys and values are pointers.

The size is automatically adjusted as associations are added and removed.

null pointers are fully supported. See <a href="@(baseurl)api/ring1-library/collections-library/Ring1_AddedCallback"><code class="inline">Ring1_Collections_AddedCallback</code></a> and
<a href="@(baseurl)api/ring1-library/collections-library/Ring1_RemovedCallback"><code class="inline">Ring1_Collections_RemovedCallback</code></a> for more information on storing null
pointers in pointer hash maps.

The "set" and "get" operations are amortized constant time in all cases.
An <code class="inline">Ring1_PointerHashMap</code> can be allocated on the stack or on the heap and can be part of struct types.
Before using the pointer hash map object, it must be initialized using <code class="inline">Ring1_PointerHashMap_initialize</code>.
When no longer required, it must be uninitialized using <code class="inline">Ring1_PointerHashMap_uninitialize</code>.
</p>

@(>"./_footer.html.t")
