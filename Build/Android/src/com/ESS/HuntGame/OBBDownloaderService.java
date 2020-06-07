/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.ESS.HuntGame;

import com.google.android.vending.expansion.downloader.impl.DownloaderService;

/**
 * Minimal client implementation of the
 * DownloaderService from the Downloader library.
 */
public class OBBDownloaderService extends DownloaderService {
    // stuff for LVL -- MODIFY FOR YOUR APPLICATION!
    private static final String BASE64_PUBLIC_KEY = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA63XlEmepsFuN0xVtc+j+BlTFQ7ksfjdlvMlXsLd09x5ode6Qg4UHTh+LAwzUbWMTsjRoMo9Mh1IsHRh45QZWvYO8ER4GYTWd3O0NexDGOnKQa8LbgTmj3p0hDHE/B4SA20EOQWvG3MA4fL/cp6RBTEjw4pi5r/8yQLcjf1uNcXvov9sy6oQnWkf0IVIDJt6M+Vh8CMCvb0xC/bgIc+in2sRm94IFhssXwo6U5vGrT1edaJ30CWDWLCjpNwOIh6CAn9j9WNSyUwRje7rcLz/lqY7xKvnqYRs9OvODiYtojTA9yLSrezv1w1XGKYp0vn37+HS03UbcuI3cZfJza1LGUwIDAQAB";
    // used by the preference obfuscater
    private static final byte[] SALT = new byte[] {
            1, 43, -12, -1, 54, 98,
            -100, -12, 43, 2, -8, -4, 9, 5, -106, -108, -33, 45, -1, 84
    };

	public static int getPublicKeyLength() {
		return BASE64_PUBLIC_KEY.length();
	}
	
    /**
     * This public key comes from your Android Market publisher account, and it
     * used by the LVL to validate responses from Market on your behalf.
     */
    @Override
    public String getPublicKey() {
        return BASE64_PUBLIC_KEY;
    }

    /**
     * This is used by the preference obfuscater to make sure that your
     * obfuscated preferences are different than the ones used by other
     * applications.
     */
    @Override
    public byte[] getSALT() {
        return SALT;
    }

    /**
     * Fill this in with the class name for your alarm receiver. We do this
     * because receivers must be unique across all of Android (it's a good idea
     * to make sure that your receiver is in your unique package)
     */
    @Override
    public String getAlarmReceiverClassName() {
        return com.ESS.HuntGame.AlarmReceiver.class.getName();
    }
}
