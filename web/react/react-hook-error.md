# Invalid hook call when using recharts pie
** my solution is to delete node_module and run cnpm i **
The error message "Invalid hook call. Hooks can only be called inside of the body of a function component." is a common React error and not specific to using Recharts. It usually occurs under a few different scenarios:

1. **You're calling a hook from a regular JavaScript function that is not a functional React component.** Hooks must be called from within functional components or from custom hooks.

2. **You're calling a hook from within a class component.** Hooks cannot be used in class components.

3. **You have multiple copies of React in your project.** This can happen if, for example, you've linked a local package that has its own React dependency.

Given that you're encountering this issue while using a Recharts `Pie` component, let's address how you might resolve it, focusing on the assumption that you're trying to use a hook within a component or function correctly:

### Ensure Proper Usage of Hooks

First, ensure that you're using the hook inside a functional component or another custom hook. A correct usage pattern looks like this:

```jsx
import React, { useState, useEffect } from 'react';
import { PieChart, Pie } from 'recharts';

const MyPieChart = () => {
  // Correct: This is inside a functional component
  const [data, setData] = useState([]);

  useEffect(() => {
    // Fetch or generate your data here
    setData([{ name: 'Group A', value: 400 }, { name: 'Group B', value: 300 }]);
  }, []); // Dependency array

  return (
    <PieChart width={400} height={400}>
      <Pie dataKey="value" isAnimationActive={false} data={data} cx={200} cy={200} outerRadius={80} fill="#8884d8" label />
    </PieChart>
  );
};

export default MyPieChart;
```

### Check for Multiple React Instances

If the usage is correct but the problem persists, you might have multiple instances of React, which can cause hooks to malfunction. This often occurs in monorepos or when using npm/yarn link for local package development. To diagnose and fix this issue:

1. **Check Your Node Modules**: Look for multiple instances of React by running `npm ls react` or `yarn why react` in your project directory.

2. **Ensure a Single React Version**: If you find multiple versions, try to resolve the version conflicts in your `package.json` file. You might need to upgrade/downgrade some packages to ensure they all rely on the same React version.

3. **Use npm/yarn Link with Caution**: If you're using `npm link` or `yarn link` for local package development, ensure that your linked package does not install its own React. One workaround is to have your package use React from the parent project by marking it as a peer dependency and using `npm link ../path/to/parent/node_modules/react` in your package's node_modules.

4. **Webpack Alias**: If you're using webpack, you can configure an alias to ensure that only one version of React is bundled, regardless of node_modules structure:

```javascript
// webpack.config.js
module.exports = {
  // ...
  resolve: {
    alias: {
      react: path.resolve('./node_modules/react'),
    },
  },
};
```

By ensuring you're using hooks correctly and that your project only contains one instance of React, you should be able to resolve the "Invalid hook call" error and use Recharts' `Pie` component without issues.

