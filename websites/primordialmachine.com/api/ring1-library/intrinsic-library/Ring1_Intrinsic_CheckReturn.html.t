@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_checkreturn">Ring1_Intrinsic_CheckReturn</h2>
<p>Issues a compile-time warning or a compile-time error
   if a compiler that supports this annotation can determine
   that the return value of an annotated function is not used.</p>

<p><code class="block">
#define Ring1_Intrinsic_CheckReturn() /* Implementation */
</code></p>

<h3>Usage Example</h3>
<p><code class="block">
Ring1_Intrinsic_CheckReturn() int f();
</code></p>

@(>"./_footer.html.t")
