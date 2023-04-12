@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="ring1_intrinsic_fp_exponentmask">Ring1_Intrinsic_Fp_ExponentMask</h2>
<code class="block">
#define Ring1_Intrinsic_Fp_ExponentMask_<em>suffix</em> /* Implementation */
</code>
<p>
where <code class="inline"><em>suffix</em></code> is
either <code class="inline">f32</code> (for the type <code class="inline">float</code>)
or <code class="inline">f64</code> (for the type <code class="inline">double</code>).
</p>
<p>
For suffix <code class="inline">f32</code>:
Symbolic constant evaluating to a <code class="inline">uint32_t</code> value.
Masks the exponent bits of the raw bits representation of a single-precision floating-point value (8 bits from index 30 to 23).
</p>
<p>
For suffix <code class="inline">f64</code>:
Symbolic constant evaluating to a <code class="inline">uint64_t</code> value.
Masks the exponent bits of the raw bits representation of a double-precision floating-point value (11 bits from index 63 to index 52). 
</p>

@(>"./_footer.html.t")
