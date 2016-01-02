/*
 * Copyright 2012 soundarapandian
 * Licensed under the Apache License, Version 2.0
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
$(document).ready(function() {
  /*Timer control
  For detailed usage visit the below link
  http://keith-wood.name/countdownRef.html
  */
  $(".timer").countdown({
    until: new Date(2016, 1 - 1, 4, 10, 30),
    labels: ['Years', 'Months', 'Weeks', 'Days', 'Hrs', 'Mins', 'Secs']
  });
});
