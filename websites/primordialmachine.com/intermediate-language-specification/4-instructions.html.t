@{title = "IL Specification: 4. Instructions"}
@{tableOfContents = "./_toc.ihtml"}
@(>"./_header.html.t")
            <p>This section of the <em>Intermediate Language Specification</em> lists all <em>instructions</em>
            of the <em>Intermediate Language</em> (<em>IL</em>).</p>

            <p>Instructions in <em>IL</em> change their semantics depending on its operands and parameters.
            This property is called <em>instruction polymorphism</em>.</p>

            <p><em>The <code class="inline">jumpIfTrue</code> instruction has different semantics depending
            on wether a label name (a parameter) is provided or not. The <code class="inline">negate</code>
            instruction has different semantics when the operand is a <code class="inline">Boolean</code>
            value, an <code class="inline">Integer</code> value, or a <code class="inline">Real</code> value.</em></p>

            <p>If program execution encounters an instruction with a combination of operands and/or parameters for which no provided semantic definition applies
            then the program execution <em>must</em> terminate.</p>

            <p><em>The <code class="inline">affirmate</code> instruction is executed
            with an operand of type <code class="inline">Array</code>.
            Semantic definitions of the instruction are provided for
            a single argument of type Boolean, Integer, or Real.
            Hence no semantic definition applies.
            Hence the execution of the program must terminate.</em></p>

            <p>Some instructions are aliases of other instructions.</p>

            <p>Note the difference between
            <code class="inline">Boolean ∪ Integer</code>
            and <code class="inline">{Boolean} ∪ {Integer}</code>.
            The former is the union of the set of all values of type <code class="inline">Boolean</code> with the set of all values of type <code class="inline">Integer</code>.
            The latter is the union of the two sets, one containing the type <code class="inline">Boolean</code> and the other the type <code class="inline">Integer</code>.
            Hence given <code class="inline">X &isin; Boolean ∪ Integer</code> then <code>X</code> is some value of type <code class="inline">Boolean</code> or of type <code class="inline">Integer</code>.
            Whilst given <code class="inline">X &isin; {Boolean} ∪ {Integer}</code> then <code>X</code> is either the type <code class="inline">Boolean</code> or the type <code class="inline">Integer</code>.
            </p>

            @(>"./intermediate-language-specification/4-instructions/and.thtml")
            @(>"./intermediate-language-specification/4-instructions/or.thtml")
            @(>"./intermediate-language-specification/4-instructions/not.thtml")
            @(>"./intermediate-language-specification/4-instructions/affirmate.thtml")
            @(>"./intermediate-language-specification/4-instructions/negate.thtml")

            @(>"./intermediate-language-specification/4-instructions/equalTo.thtml")
            @(>"./intermediate-language-specification/4-instructions/notEqualTo.thtml")
            @(>"./intermediate-language-specification/4-instructions/lowerThan.thtml")
            @(>"./intermediate-language-specification/4-instructions/lowerThanOrEqualTo.thtml")
            @(>"./intermediate-language-specification/4-instructions/greaterThan.thtml")
            @(>"./intermediate-language-specification/4-instructions/greaterThanOrEqualTo.thtml")

            @(>"./intermediate-language-specification/4-instructions/add.thtml")
            @(>"./intermediate-language-specification/4-instructions/subtract.thtml")
            @(>"./intermediate-language-specification/4-instructions/multiply.thtml")
            @(>"./intermediate-language-specification/4-instructions/divide.thtml")
            @(>"./intermediate-language-specification/4-instructions/storeLocal.thtml")
            @(>"./intermediate-language-specification/4-instructions/loadLocal.thtml")
@(>"./_footer.html.t")
