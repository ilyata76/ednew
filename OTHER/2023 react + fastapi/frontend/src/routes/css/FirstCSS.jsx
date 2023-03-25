import React from "react";

import styles from "./first.module.css";

const FirstCSS = () => {
    return (
        <React.Fragment>
            <h1 className={styles.h1_name}>h1 first</h1>
            <p className={styles.p_name}>p first</p>
        </React.Fragment>
    );
};

export default FirstCSS;