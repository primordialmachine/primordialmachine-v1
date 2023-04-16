@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_fp_signbits">Ring1_Intrinsic_Fp_SignBits</h2>
<code class="block">
#define Ring1_Intrinsic_Fp_SignBits_<em>suffix</em> /* Implementation */
</code>
<p>
where <code class="inline"><em>suffix</em></code> is
either <code class="inline">f32</code> (for the type <code class="inline">float</code>)
or <code class="inline">f64</code> (for the type <code class="inline">double</code>).
</p>
<p>
Symbolic constant evaluating to an integer value 1 (both for suffix <code class="inline">f32</code> and suffix <code class="inline">f64</code>),
denoting the number of sign bits both of a IEEE754 32 bit floating-point value and a IEEE754 64 bit floating-point value, respectively.
</p>

@(>"./_footer.html.t")
