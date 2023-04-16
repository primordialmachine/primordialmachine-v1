<!DOCTYPE html>
<html lang="en">
  <head>
    @(>"./head-enter.ihtml")
    <title>@(title)</title>
    <meta name="generator" content="@(GeneratorVendor()) @(GeneratorName())"/>
    <meta name="google-site-verification" content="sGmOwdhzfdWaPQRvjnImdJfSHYWtpKt3REFyzGpDKDU" />

    <link rel="icon" href="/favicon.svg">

  </head>
  <body>
    <div class="container-fluid">
      <header class="d-flex flex-row align-items-center justify-content-between">
          @* Hide logo on smaller than or equal to extra small. *@
          <div class="my-logo d-none d-sm-block">
            <h1><a href="@(baseurl)"><span style="display:block">@(websiteTitle)</span></a></h1>
          </div>
          @* Show on smaller than small. *@
          <button type="button" class="d-block d-sm-none btn btn-dark"
                  data-toggle="collapse" data-target=".overlay-multi-collapse"
                  role="button" aria-expanded="false" aria-controls="my-navigation-overlay">
            <i class="fa fa-bars"></i>
          </button>
      </header>

      <div class="d-block d-sm-none row">
        <div class="col">
          <div id="my-navigation-overlay" style="overflow: auto" class="toc my-navigation-overlay collapse overlay-multi-collapse">
            <div class="card">
              <div class="card-header">
                <button type="button" class="close" aria-label="Close"
                        data-toggle="collapse" data-target=".overlay-multi-collapse"
                        role="button" aria-expanded="false" aria-controls="my-navigation-overlay my-article">
                  <span aria-hidden="true">&times;</span>
                </button>
              </div>
              <div class="card-body">
                @(>tableOfContents)
              </div>
            </div>
          </div>
        </div>
      </div>

      <main class="row">
        @(>"header-enter.ihtml")
        @* 3 columns on greater than small. Hidden on small or lower. *@
        <nav class="toc col col-sm-3 d-none d-sm-block">
          @(>tableOfContents)
        </nav>
        @* 9 rows on all other screen sizes than small. 12 on small or lower. *@
        <article id="my-article" class="col col-sm-9 pl-md-5 pr-md-5 collapse overlay-multi-collapse show">