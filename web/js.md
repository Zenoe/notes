##  `parentNode` vs `parentElement`
- `parentNode` return any type of node, including elements (like `<div>`, `<svg>`, etc.), document nodes (like the `document` object), and even text nodes.
- `parentElement` returns the parent element of the specified node, but only if the parent is an element node.

```html
<div id="container">
  Text Node
  <span id="mySpan">Hello</span>
</div>
<script>
  const span = document.getElementById('mySpan');

  console.log(span.parentNode);      // Outputs: <div id="container">...</div>
  console.log(span.parentNode.nodeType); // Outputs: 1 (Node.ELEMENT_NODE)

  // Using parentElement
  console.log(span.parentElement);    // Outputs: <div id="container">...</div>
  console.log(span.parentElement.nodeType); // Outputs: 1 (Node.ELEMENT_NODE)

  // Accessing a text node
  const textNode = span.childNodes[0]; // This is a text node
  console.log(textNode.parentNode);      // Outputs: <span id="mySpan">Hello</span>
  console.log(textNode.parentElement);   // Outputs: null (because text nodes don't have an element parent)
</script>
```

## reduce
      const closestPoint = targetPoints.reduce((prev, curr) =>
        Math.hypot(curr.x - endPoint.x, curr.y - endPoint.y) <
        Math.hypot(prev.x - endPoint.x, prev.y - endPoint.y)
          ? curr
          : prev
      )
