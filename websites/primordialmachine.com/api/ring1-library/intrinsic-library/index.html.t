@{title = "Ring 1 :: Intrinsic Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")
  <section>
    <h2>Overview</h2>
    <p>The <em>Intrinsic</em> library provides <em>intrinsic functions and macros</em>:</p>
    <ul class="cutelist">
      <li>Get next power of two greater than or equal a given integer value.</li>
      <li>Get the next multiple of 32 or 64 greater than or equal to a integer given value.</li>
      <li>Safely compute the sums, the products, and the differences of integers.</li>
      <li>Macros for guiding the compiler's diagnostics and optimizations.</li>
    </ul>

    <p>The <em>Intrinsic</em> library fulfils the <a href="@(baseurl)api/ring1-library/introduction.html">module concept</a>
    but does not require initialization.</p>

    <p>The include file of the <em>Intrinsic</em> library is <code class="inline">Ring1/Intrinsic.h</code>,
    its library file is <code class="inline">Ring1.lib</code>.</p>
  
    <h2>Sources and references</h2>
    <p>The <a href="@(repositoryUrl)/src/master">reference repository</a> provides non-authoritive
    <a href="@(repositoryUrl)/src/master/ring1/">sample implementations</a>.</p>
  </section>
@(>"./_footer.html.t")
