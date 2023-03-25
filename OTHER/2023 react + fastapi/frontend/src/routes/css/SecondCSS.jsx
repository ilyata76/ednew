import React from "react";

import styles from "./second.module.css";

const SecondCSS = () => {
    return (
        <React.Fragment>
            <h1 className={styles.h1_name}>h1 second</h1>
            <p className={styles.p_name}>p second</p>
        </React.Fragment>
    );
};

export default SecondCSS;