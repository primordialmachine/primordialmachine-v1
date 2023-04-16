@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_threadlocal">Ring1_Intrinsic_ThreadLocal</h2>
<p>Storage class specifier annotating an object as having thread local storage duration.</p>

<p><code class="block">
#define Ring1_Intrinsic_ThreadLocal() /* Implementation */
</code></p>

<h3>Usage Example</h3>
<p><code class="block">
Ring1_Intrinsic_ThreadLocal() static int g_counter = 0;
</code></p>

@(>"./_footer.html.t")
