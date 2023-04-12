@{title = "IL Specification: 2. Method of Description and Notation"}
@{tableOfContents = "./_toc.ihtml"}
@(>"./_header.html.t")
            <h2>Method of Description and Notation</h2>
            <p>The form of an <em>Intermediate Language</em> program is described by means of a context-free syntax
            with  context-dependent rules.
            Rules are both stated in natural language and in mathematical language.</p>

            <p>The meaning of an <em>Intermediate Language</em> program is described by means of rules describing the effect
            of each language construct and rules describing the composition of language constructs. Both kinds of rules are
            both stated in natural language and in mathematical language.</p>

            <p>The context-free syntax of the language is described using a variant of Backus-Naur Form.</p>

            <p>
            Backus-Naur Form context-free rules are set in typewriter front.
            Boldface front is used to denote terminals, for example <code class="inline" style="font-weight: bold">.class</code>.
            Pascal-case words are used to denote non terminals, for example <code class="inline">Program</code>.
            <ul style="list-style: none; margin-top: 2em;">
              <li style="margin-bottom: 2em;">
                Square brackets enclose optional items. Thus the following two rules are effectively equivalent:
                <div><code class="block">
                jumpStatement = <span style="font-weight: bold">jump</span>&nbsp;[Label]<br/>
                jumpStatement = <span style="font-weight: bold">jump</span>&nbsp;Label<br/>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                | <span style="font-weight: bold">jump</span>
                </code></div>
              </li>
              <li style="margin-bottom: 2em;">
                <code class="inline">&epsilon;</code> denotes the empty word.
              </li>
              <li style="margin-bottom: 2em;">
                Curly brackets enclose repeated items. The item may appear zero or more times; the repetitions occur from left to right as
                with an equivalent left-recursive rule. Thus the following two rules are effectively equivalent:
                <div><code class="block">
                structureBodyElements = {structureBodyElement}<br/>
                structureBodyElements = &epsilon;<br/>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                | structureBodyElement structureBodyElements
                </code></div>
              </li>
              <li>
                A vertical line separates alternative items. For example, the following rules denotes that <code class="inline">constantLiteral</code>
                is a choice between <code class="inline">booleanLiteral</code>, <code class="inline">stringLiteral</code>,
                <code class="inline">numberLiteral</code>, or <code class="inline">voidLiteral</code>.
                <div><code class="block">
                constantLiteral = booleanLiteral | stringLiteral | numberLiteral | voidLiteral
                </code></div>
              </li>
            </ul>
            </p>


            <p style="color: orange">
            To be done: Description of the notation of context-dependent rules.
            </p>

            <p>A language construct is a piece of text (explicit or implicit) that is an instance of a context-free rule.</p>

            <p style="color: orange">
            To be done: (Notation of) a rule describing the effect of a language construct.
            </p>
            <p style="color: orange">
            To be done: (Notation of) a rule describing the composition of language constructs.
            </p>
@(>"./_footer.html.t")
