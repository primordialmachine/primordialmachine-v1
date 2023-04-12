@* Copyright (c) 2019-2022 Michael Heilmann. All rights reserved. *@

@(>"./font-style-2020-07-22.tcss")
@(>"./code-style.tcss")

html, article {
  scroll-behavior: smooth;
}

body {
  overflow: hidden;
}

@* For lists in text, we want square bullets. *@
main ul
{
  list-style-type: square;
}

.nav ul
{
  list-style: none;
}

.nav ul li a
{
  white-space: nowrap;
}

@*
<dl class="parameters">
  <dd><code class="x"></dd><dt>The value.</dt>
</dl>
*@
dl.parameters > dt
{
  float: left;
  clear: left;
  margin-right: 1em;
}



@* Put a little placeholder on top of the page. Will become a logo or something later. *@
header > div.row:first-child > div.col-sm-12
{
  padding: 0; @* Override 15px left and right padding added by Bootstrap 4. *@
}

header > div.row:first-child > div.col-sm-12 > span
{
  display: block;
  background-color: white;
  min-height: 5em;
}

body
{
  height: 100vh;
  max-height: 100vh;
  display: flex;
  flex-direction: column;
  flex: 0;
}

body div.container-fluid {
  height: 100%;
  max-height: 100%;
  flex: 1; @* TODO: Is this required? *@
  flex-direction: column;
  display: flex;
}

main
{
  margin-top: 0; @* TODO The margin of main was set to 2 somewhere. We reset it here but this should not be required. *@
  min-height: 0; @* Normally elements do not shrink beyond their natural width. Set min-height to 0 to change this behavior. *@
}

@*
This makes the list a little bit longer than its list items for that we can "overscroll" a bit. 
TODO The appropriate Bootstrap classes were already added to the relevant parts so I do not think this is necessary.
*@
main > nav > ul
{
  @* This makes the list a little bit longer than its list items for that we can "overscroll" a bit. *@
  margin-bottom: 1em !important;
  
  @* Ensure there is always 1 column and n rows for n elements. *@
  flex-wrap: nowrap;
  flex-direction: column;
}

@* This makes the column extend to the bottom of the page. If the content is still longer than the page, a vertical scrollbar is added. *@
body main article.col, body main nav.col
{
  height: 100%;
  max-height: 100%;
  overflow-y: auto; @* Show scrollbars if necessary. *@
  position: relative;
}

@* This ensure that MathJax equations all have the same left margin. *@
mjx-container[jax="CHTML"][display="true"] {
  text-align: left !important;
  padding-left: 0px;
}

.my-formula {
  padding-left: 1.5em;
}

.my-formula.my-reason {
  border-left-style: solid;
  border-left-width: 1em;
  border-left-color: #d9edf7;
  padding-left: 0.5em !important;
  background-color: white;
  padding-top: 1em;
  padding-bottom: 1em;
  
  border-top-right-radius: 2px;
  border-bottom-left-radius: 2px;
  border-bottom-right-radius: 2px;
  border-top-left-radius: 2px;

  
  border-top-style: solid;
  border-top-width: 1px;
  border-top-color: #bce8f1;
  
  border-bottom-style: solid;
  border-bottom-width: 1px;
  border-bottom-color: #bce8f1;
  
  border-right-style: solid;
  border-right-width: 1px;
  border-right-color: #bce8f1;
}

.my-formula.my-result {
  border-left-style: solid;
  border-left-width: 1em;
  border-left-color: white;
  padding-left: 0.5em !important;
}

@(>"./toc.tcss")
@(>"./my/codedoc.css.i")
