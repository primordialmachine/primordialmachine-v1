@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_unlikely">Ring1_Intrinsic_Unlikely</h2>
<p>Annotation an integral expression as likely to evaluate to a zero integral value.</p>

<p><code class="block">
#define Ring1_Intrinsic_Unlikely(expression) /*Implementation.*/
</code></p>

<h3>Parameters</h3>
<dl class="parameters">
  <dt><code class="inline">expression</code></dt>
  <dd>The expression.</dd>
</dl>

<h3>Remarks</h3>
<p>
The annotation provides branch prediction information to the compiler.
This annotation must be used with an integral expression.
The compiler is informed, that this integral expression is likely to evaluate an integral value which in turn evaluates to logically true.
</p>

@(>"./_footer.html.t")
