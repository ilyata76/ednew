import React from "react";

const RouterIframe = ({iframe}) => { // (props) ==>> props.iframe
    return (
        <div dangerouslySetInnerHTML = { { __html:  iframe ? iframe : "" } }/>
    );
}

export default RouterIframe;