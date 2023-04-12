@{title = "Ring 1 :: Pointer List Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_pointerlist">Ring1_PointerList</h2>
<p>The type of a pointer list.</p>
<p><code class="block">
typedef struct Ring1_PointerList { ... } Ring1_PointerList;<br/>
</code></p>

<p>
A list of pointers. The size is automatically adjusted as pointers are added and removed.
null pointers are fully supported.
See
<code style="word-break: break-all" class="inline">Ring1_PointerList_AddedCallback</code>
and
<code style="word-break: break-all" class="inline">Ring1_PointerList_RemovedCallback</code>
for more information on storing null pointers in pointer lists.

The "appendPointer" and "accessPointer" operations are constant time in all cases,
the "insertPointer" operation linear time in worst case.

An <code class="inline">Ring1_PointerList</code> can be allocated on the stack or on the heap and can be part of struct types.
Before using the pointer list object, it must be initialized using <code class="inline">Mkx_PointerList_initialize</code>.
When no longer required, it must be uninitialized using <code class="inline">Mkx_PointerList_uninitialize</code>.
</p>

@(>"./_footer.html.t")
