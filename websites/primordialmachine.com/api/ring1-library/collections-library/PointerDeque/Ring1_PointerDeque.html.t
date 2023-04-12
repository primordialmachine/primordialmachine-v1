@{title = "Ring 1 :: Collection Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h3 id="ring1_pointerdeque">Ring1_PointerDeque</h3>
<p>The type of a pointer deque.</p>
<p><code class="block">
typedef struct Ring1_PointerDeque { ... } Ring1_PointerDeque;<br/>
</code></p>

<p>
A deque of pointers.

The size is automatically adjusted as pointers are added and removed.

null pointers are fully supported. See <a href="@(baseurl)api/ring1-library/collections-library/Ring1_AddedCallback"><code class="inline">Ring1_AddedCallback</code></a> and
<a href="@(baseurl)api/ring1-library/collections-library/Ring1_RemovedCallback"><code class="inline">Ring1_RemovedCallback</code></a> for more information on storing null
pointers in pointer deques.

The "append" and "getAt" operations are constant time in all cases, the "insert" operation linear time in worst case.
An <code class="inline">Mkx_PointerDeque</code> can be allocated on the stack or on the heap and can be part of struct types.
Before using the pointer deque object, it must be initialized using <code class="inline">Ring1_PointerDeque_initialize</code>.
When no longer required, it must be uninitialized using <code class="inline ">Ring1_PointerDeque_uninitialize</code>.
</p>

@(>"./_footer.html.t")
