@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_noreturn">Ring1_Intrinsic_NoReturn</h2>
<p>Function annotation indicating a function does not return the usual way or does not return at all.
   Surpresses the usual compile-time warnings or compile-time errors
   if a function does not return the usual way or does not return at all. </p>

<p><code class="block">
#define Ring1_Intrinsic_NoReturn() /* Implementation */
</code></p>

<h3>Usage Example</h3>
<p><code class="block">
Ring1_Intrinsic_NoReturn() void f();
</code></p>

@(>"./_footer.html.t")
