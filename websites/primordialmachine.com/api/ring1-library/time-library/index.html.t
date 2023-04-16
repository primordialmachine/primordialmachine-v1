@{title = "Ring 1 :: Time Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")
  <section>
    <h2>Overview</h2>
    <p>The <em>Time</em> library provides <em>time functionality.</em>.</p>

    <p>The <em>Time</em> library fulfils the <a href="@(baseurl)api/ring1-library/introduction.html">module concept</a>
    i.e. provides
    the type <code class="inline">Ring1_Time_ModuleHandle</code>,
    the constant <code class="inline">Ring1_Time_ModuleHandle_Invalid</code>, and
    the functions <code class="inline">Ring1_Time_ModuleHandle_acquire</code> and <code class="inline">Ring1_Time_ModuleHandle_relinquish</code>.</p>
    
    <p>The include file of the <em>Time</em> library is <code class="inline">Ring1/Time.h</code>,
    its library file is <code class="inline">Ring1.lib</code>.</p>
  
    <h2>Sources and references</h2>
    <p>The <a href="@(repositoryUrl)/src/master">reference repository</a> provides non-authoritive
    <a href="@(repositoryUrl)/src/master/ring1/">sample implementations</a>.</p>
  </section>
@(>"./_footer.html.t")
