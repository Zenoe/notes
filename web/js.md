 `parentNode` vs `parentElement`
### `parentNode`

- **Definition**: `parentNode` returns the parent node of the specified node in the DOM tree.
- **Return Type**: It can return any type of node, including elements (like `<div>`, `<svg>`, etc.), document nodes (like the `document` object), and even text nodes.
- **Use Case**: Use `parentNode` when you need to access the parent of any node type, including non-element nodes.

### `parentElement`

- **Definition**: `parentElement` returns the parent element of the specified node, but only if the parent is an element node.
- **Return Type**: It returns an `Element` object (or `null` if the parent is not an element, such as when the parent is the document or a text node).
- **Use Case**: Use `parentElement` when you specifically want to work with an element node and you want to ensure that the parent is an element.

### Key Differences

1. **Return Value**:
   - `parentNode`: Can return any node type (including `Document`, `DocumentFragment`, or `Text` nodes).
   - `parentElement`: Returns only an `Element` node or `null`.

2. **Use in Practice**:
   - If you are sure that the parent will always be an element (e.g., in a typical HTML structure), you can use `parentElement` for clarity.
   - If you need to handle cases where the parent might not be an element, use `parentNode`.

### Example

Here’s an example to illustrate the difference:

```html
<div id="container">
  Text Node
  <span id="mySpan">Hello</span>
</div>

<script>
  const span = document.getElementById('mySpan');

  // Using parentNode
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

### Summary

- Use `parentNode` when you want to be agnostic about the type of the parent node.
- Use `parentElement` when you specifically want to ensure the parent is an element and handle it accordingly.

## reduce
      const closestPoint = targetPoints.reduce((prev, curr) =>
        Math.hypot(curr.x - endPoint.x, curr.y - endPoint.y) <
        Math.hypot(prev.x - endPoint.x, prev.y - endPoint.y)
          ? curr
          : prev
      )

      if (
        Math.hypot(closestPoint.x - endPoint.x, closestPoint.y - endPoint.y) <
        10
      ) {
        const pathData = calculateOrthogonalPath(d.startPoint, closestPoint)
        d.line.attr('d', pathData)
        endPoint.connected = true
      }
